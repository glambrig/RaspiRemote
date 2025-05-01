#ifndef UINPUTWRAPPERLIB_H
# define UINPUTWRAPPERLIB_H

# ifdef __cplusplus
extern "C"
{
# endif

# define NB_BUTTONS 41
# define KEY_EVENT 0
# define MOUSE_EVENT 1

# include <linux/input.h>
# include <linux/uinput.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

struct screensize
{
	u_int16_t x;
	u_int16_t y;
};

/*
*	initializes the uinput device and returns a file descriptor corresponding to it, or -1 if an error occurred
*/
int setup_device(const char *device_name, const char *path_to_uinput);

/*
*	sends any event to a device.
*
*	device_fd: file descriptor got from setup_device()
*	which_key: the key or button that is to be simulated (see /usr/include/linux/input-event-codes.h)
*	key_value: 0 for unpressed, 1 for pressed, or offset for mouse movement
*	event_type: either KEY_EVENT or MOUSE_EVENT
*	release_key_after_ms: how long the key should stay pressed, or 0 for instant press and release
*/
int	send_event_to_device(int device_fd, unsigned int which_key, int key_value, int event_type, u_int32_t release_key_after_ms);

/*
*	simulates a click
*/
int	click(int device_fd, u_int32_t release_key_after_ms);

/*
*	simulates a keypress
*/
int	press_key(int device_fd, u_int16_t key, u_int32_t release_key_after_ms);

/*
*	moves the mouse to the absolute coordinates specified
*/
int	move_mouse_to_pos(int device_fd, int16_t x, int16_t y, struct screensize screensize);

/*
*	moves the mouse relative to the current mouse position
*/
int	move_mouse_from_cursor(int device_fd, int16_t x, int16_t y);

/*
*	destroys the device and frees associated memory
*/
int	cleanup_device(int device_fd);

# ifdef __cplusplus
}
# endif

# ifdef __cplusplus
namespace uinputWrapperLib
{
	/*
	*	initializes the uinput device and returns a file descriptor corresponding to it, or -1 if an error occurred
	*/
	inline int setup_device(const char *device_name, const char *path_to_uinput)
	{
        return (::setup_device(device_name, path_to_uinput));
    }

	/*
	*	sends any event to a device.
	*
	*	device_fd: file descriptor got from setup_device()
	*	which_key: the key or button that is to be simulated (see /usr/include/linux/input-event-codes.h)
	*	key_value: 0 for unpressed, 1 for pressed, or offset for mouse movement
	*	event_type: either KEY_EVENT or MOUSE_EVENT
	*	release_key_after_ms: how long the key should stay pressed, or 0 for instant press and release
	*/
    inline int send_event_to_device(int device_fd, unsigned int which_key, int key_value, int event_type, u_int32_t release_key_after_ms)
	{
        return (::send_event_to_device(device_fd, which_key, key_value, event_type, release_key_after_ms));
    }

	/*
	*	simulates a click
	*/
	inline int	click(int device_fd, u_int32_t release_key_after_ms)
	{
        return (::click(device_fd, release_key_after_ms));
    }

	/*
	*	simulates a keypress
	*/
	inline int	press_key(int device_fd, u_int16_t key, u_int32_t release_key_after_ms)
	{
        return (::press_key(device_fd, key, release_key_after_ms));
    }

	/*
	*	moves the mouse to the absolute coordinates specified
	*/
    inline int move_mouse_to_pos(int device_fd, int32_t x, int32_t y, struct screensize screensize)
	{
        return (::move_mouse_to_pos(device_fd, x, y, screensize));
    }

	/*
	*	moves the mouse relative to the current mouse position
	*/
	inline int	move_mouse_from_cursor(int device_fd, int16_t x, int16_t y)
	{
        return (::move_mouse_from_cursor(device_fd, x, y));
	}

	/*
	*	destroys the device and frees associated memory
	*/
    inline int cleanup_device(int device_fd)
	{
        return (::cleanup_device(device_fd));
    }
}	//namespace
# endif

#endif