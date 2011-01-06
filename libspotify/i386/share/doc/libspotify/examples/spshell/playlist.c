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
int cmd_playlists(int argc, char **argv)
{
	sp_playlistcontainer *pc = sp_session_playlistcontainer(g_session);
	int i, j, level = 0;
	sp_playlist *pl;

	printf("%d entries in the container\n", sp_playlistcontainer_num_playlists(pc));

	for (i = 0; i < sp_playlistcontainer_num_playlists(pc); ++i) {
		switch (sp_playlistcontainer_playlist_type(pc, i)) {
			case SP_PLAYLIST_TYPE_PLAYLIST:
				printf("%d. ", i);
				for (j = level; j; --j) printf("\t");
				pl = sp_playlistcontainer_playlist(pc, i);
				printf("%s\n", sp_playlist_name(pl));
				break;
			case SP_PLAYLIST_TYPE_START_FOLDER:
				printf("%d. ", i);
				for (j = level; j; --j) printf("\t");
				printf("Folder: %s with id %llu\n",
					   sp_playlistcontainer_playlist_folder_name(pc, i),
					   sp_playlistcontainer_playlist_folder_id(pc, i));
				level++;
				break;
			case SP_PLAYLIST_TYPE_END_FOLDER:
				level--;
 				printf("%d. ", i);
				for (j = level; j; --j) printf("\t");
				printf("End folder with id %llu\n",	sp_playlistcontainer_playlist_folder_id(pc, i));
				break;
			case SP_PLAYLIST_TYPE_PLACEHOLDER:
				printf("%d. Placeholder", i);
				break;
		}
	}
	return 1;
}

/**
 *
 */
int cmd_playlist(int argc, char **argv)
{
	int index, i;
	sp_track *track;
	sp_playlist *playlist;
	sp_playlistcontainer *pc = sp_session_playlistcontainer(g_session);

	if (argc < 1) {
		printf("playlist [playlist index]\n");
		return 0;
	}

	index = atoi(argv[1]);
	if (index < 0 || index > sp_playlistcontainer_num_playlists(pc)) {
		printf("invalid index\n");
		return 0;
	}
	playlist = sp_playlistcontainer_playlist(pc, index);
	printf("Playlist %s by %s%s%s\n",
		   sp_playlist_name(playlist),
		   sp_user_display_name(sp_playlist_owner(playlist)),
		   sp_playlist_is_collaborative(playlist) ? " (collaborative)" : "",
		   sp_playlist_has_pending_changes(playlist) ? " with pending changes" : ""
		   );
	for (i = 0; i < sp_playlist_num_tracks(playlist); ++i) {
		track = sp_playlist_track(playlist, i);
		printf("%d. %c %s%s %s\n", i,
			   sp_track_is_starred(g_session, track) ? '*' : ' ',
			   sp_track_is_local(g_session, track) ? "local" : "     ",
			   sp_track_is_autolinked(g_session, track) ? "autolinked" : "          ",
			   sp_track_name(track));
	}
	return 1;
}

/**
 *
 */
int cmd_set_autolink(int argc, char **argv)
{
	int index; 
	bool autolink;
	sp_playlist *playlist;
	sp_playlistcontainer *pc = sp_session_playlistcontainer(g_session);

	if (argc < 2) {
		printf("set autolink [playlist index] [0/1]\n");
		return 0;
	}

	index = atoi(argv[1]);
	autolink = atoi(argv[2]);
	if (index < 0 || index > sp_playlistcontainer_num_playlists(pc)) {
		printf("invalid index\n");
		return 0;
	}
	playlist = sp_playlistcontainer_playlist(pc, index);
	sp_playlist_set_autolink_tracks(playlist, !!autolink);
	printf("Set autolinking to %s on playlist %s\n", autolink ? "true": "false", sp_playlist_name(playlist));
	return 1;
}
