#include <stdio.h>
#include <artsc.h>

int
main (
  int argc,
  char * * argv ) {
  arts_stream_t stream;
  int rc;

	int cfgSamplingRate = 44100;
	int cfgBits = 16;
	int cfgChannels = 2;

    rc = arts_init();
    fprintf(stderr, "d1: %d\n", rc);
    stream = arts_play_stream( cfgSamplingRate, cfgBits, cfgChannels, "xine" );
    //stream = arts_play_stream( 0, 0, 0, "artsccat" );
    arts_stream_get(stream, ARTS_P_TOTAL_LATENCY);
    fprintf(stderr, "d0: %p\n", stream);
    return (0);
}
