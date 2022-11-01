#include <io.h>

/* Decides how to proceed depending on screen to write */
int writeDispatcher(unsigned int fd, const char * buf, unsigned int count) 
{
	char format;

	if(fd % 2 != 0)				// notar que solo los pares son ERROR
		format = STDOUT_COLOR;
	else 
		format = STDERR_COLOR;

	switch(fd) {
		case BACKGROUND:
			break;

		case STDERR:							// mismo codigo
		case STDOUT:
			write(buf, format, count, normalOffset(), START_LEFT, NORMAL_MODE_LENGTH, NORMAL_MODE_STEP);
			resetLeft();
			resetRight();
		break;

		case STDERR_LEFT:
		case STDOUT_LEFT:
			write(buf, format, count, leftOffset(), START_LEFT, SPLIT_MODE_LENGTH, SPLIT_MODE_STEP);
			resetNormal();
		break;

		case STDERR_RIGHT:
		case STDOUT_RIGHT:
			write(buf, format, count, rightOffset(), START_RIGHT, SPLIT_MODE_LENGTH, SPLIT_MODE_STEP);
			resetNormal();
		break;

		default:
			// the rest of the FDs are considered pipe IDs
			return write_to_pipe(fd, buf,count);

	}

    return count;
}

/* Decides how to proceed depending on where to read */
int readDispatcher(unsigned int fd, char * buf, unsigned int count) 
{
	if(fd == STDIN) {										// Eligimos posicion de donde leer. Tambien lo podriamos hacer con una funcion/tabla
		while( !checkIfAvailableKey()){
			alter_process_state(get_current_pid(), WAITING_FOR_INPUT);
			forceChangeTask();					// Se bloquea
		}
		return consume_kb_buffer(buf,count);		// Si el key buffer no esta vacio, primero tengo que consumirlo
	}

	// The rest of the FDs are considered pipe IDs
	return read_from_pipe(fd, buf, count);;
}