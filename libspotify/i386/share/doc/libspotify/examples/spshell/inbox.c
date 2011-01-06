/**
 * Copyright (c) 2006-2010 Spotify Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <string.h>

#include "spshell.h"
#include "cmd.h"

/**
 *
 */
static void post_usage(void)
{
	fprintf(stderr, "Usage: post <recipient> [<track-uri> ...]\n");
}


/**
 * Callback for libspotify
 *
 * @param result    The inbox result object that is now done
 * @param userdata  The opaque pointer given to sp_inbox_post_tracks()
 */
static void inbox_post_completed(sp_inbox *result, void *userdata)
{
	fprintf(stderr, "Inbox post result: %s\n", sp_error_message(sp_inbox_error(result)));
	cmd_done();

}

/**
 *
 */
int cmd_post(int argc, char **argv)
{
	int num_tracks, i;
	sp_track **tracks;
	sp_link *link;

	if (argc < 2) {
		post_usage();
		return -1;
	}

	if (argc == 2) {
		// No arguments, rickroll recipient
		tracks = malloc(sizeof(sp_track *));
		link = sp_link_create_from_string("spotify:track:6JEK0CvvjDjjMUBFoXShNZ");
		sp_track_add_ref(tracks[0] = sp_link_as_track(link));
		sp_link_release(link);
		num_tracks = 1;
	} else {
		tracks = malloc(sizeof(sp_track *) * (argc - 2));
		num_tracks = 0;
		for(i = 2; i < argc; i++) {
			link = sp_link_create_from_string(argv[i]);
			if(link == NULL || !(sp_link_type(link) == SP_LINKTYPE_TRACK || sp_link_type(link) == SP_LINKTYPE_LOCALTRACK))
				continue;
			sp_track_add_ref(tracks[num_tracks++] = sp_link_as_track(link));
			sp_link_release(link);
		}
	}

	sp_inbox_post_tracks(g_session, argv[1], tracks, num_tracks, inbox_post_completed, NULL);

	for(i = 0; i < num_tracks; i++)
		sp_track_release(tracks[i]);
	free(tracks);

	return 0;
}



/**
 *
 */
int cmd_inbox(int argc, char **argv)
{
	sp_playlist *inbox;
	inbox = sp_session_inbox_create(g_session);
	if (!inbox) {
		printf("Inbox not loaded\n");
		return -1;
	}
	browse_playlist(inbox);
	return 0;
}
