#include <stdio.h>
#include <xine/xineutils.h>

int
main (
  int argc,
  char * * argv ) {
  xine_t * pengine;
  int i;
  const char * const * drivers = NULL;
  xine_audio_port_t * audio;
  xine_video_port_t * video;
    pengine = xine_new();
    xine_init(pengine);
    xine_engine_set_param(pengine, XINE_ENGINE_PARAM_VERBOSITY, 99);
    drivers = xine_list_audio_output_plugins(pengine);
    for (i = 0; drivers[i]; i ++) {
      fprintf(stderr, "d0: %s\n", drivers[i]);
    }
    //fprintf(stderr, "d: %p\n", xine_open_audio_driver(pengine, "alsa", NULL));
    fprintf(stderr, "d: %p\n", (audio = xine_open_audio_driver(pengine, "auto", NULL)));
    fprintf(stderr, "d: %p\n", (video = xine_open_video_driver(pengine, "auto", XINE_VISUAL_TYPE_X11, (void *) &(m_x11Visual));
    xine_stream_new(pengine, audio, video);
    xine_exit(pengine);
}
