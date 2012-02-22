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

#include "spshell.h"
#include "cmd.h"

#if SPOTIFY_WITH_SOCIAL
static const char *relationtypes[] = {
	"Unknown",
	"No relation",
	"Unidirectional",
	"Bidirectional"
};

/**
 *
 */
int cmd_friends(int argc, char **argv)
{
	int nf = sp_session_num_friends(g_session);
	int i;

	for(i = 0; i < nf; i++) {
		sp_user *u = sp_session_friend(g_session, i);
		sp_relation_type rt = sp_user_relation_type(g_session, u);

		printf("  %-20s [%s]\n", sp_user_canonical_name(u), relationtypes[rt]);
		printf("\tSpotify displayname: %s\n", sp_user_display_name(u));
		printf("\t           Realname: %s\n", sp_user_full_name(u));
		printf("\t            Picture: %s\n", sp_user_picture(u));
		printf("\n");
	}
	return 1;
}
#endif


static const char *getowner(sp_playlistcontainer *pc)
{
	return sp_user_canonical_name(sp_playlistcontainer_owner(pc));
}

void plc_pl_added(sp_playlistcontainer *pc, sp_playlist *playlist, int position, void *userdata)
{
	printf("playlistcontainer for user %s: pl %s added at position %d\n",
	       getowner(pc), sp_playlist_name(playlist), position);
	
}
void plc_pl_removed(sp_playlistcontainer *pc, sp_playlist *playlist, int position, void *userdata)
{
	printf("playlistcontainer for user %s: pl %s removed at position %d\n",
	       getowner(pc), sp_playlist_name(playlist), position);

}
void plc_pl_moved(sp_playlistcontainer *pc, sp_playlist *playlist, int position, int new_position, void *userdata)
{
	printf("playlistcontainer for user %s: pl %s moved from %d to %d\n",
	       getowner(pc), sp_playlist_name(playlist), position, new_position);
}

void plc_loaded(sp_playlistcontainer *pc, void *userdata)
{
	printf("playlistcontainer for user %s loaded\n", getowner(pc));
}

sp_playlistcontainer_callbacks plc_callbacks = {
	plc_pl_added,
	plc_pl_removed,
	plc_pl_moved,
	plc_loaded,
};

int cmd_published_playlists(int argc, char **argv)
{
	const char *user = NULL;
	int n;
	static sp_playlistcontainer *plc;
	sp_user *ui;

	if (argc > 1)
		user = argv[1];

	if(plc != NULL) {
		// Release any previously created playlistcontainer
		// ie. we only subscribe to one at a time
		sp_playlistcontainer_remove_callbacks(plc, &plc_callbacks, NULL);
		sp_playlistcontainer_release(plc);
	}

	plc = sp_session_publishedcontainer_for_user_create(g_session, user);

	ui = sp_playlistcontainer_owner(plc);
	printf("playlistcontainer for user %s\n", ui ? sp_user_display_name(ui) : "<unknown>");

	sp_playlistcontainer_add_callbacks(plc, &plc_callbacks, NULL);

	for (n = sp_playlistcontainer_num_playlists(plc); n; --n) {
		sp_playlist *pl = sp_playlistcontainer_playlist(plc, n);
		if (pl) {
			printf("playlist: %s\n", sp_playlist_name(pl));
		} else {
			printf("unknown playlist at position %d\n", n);
		}
	}
	return 1;
}
