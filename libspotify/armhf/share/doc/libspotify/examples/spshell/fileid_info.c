/**
 * Copyright (c) 2006-2011 Spotify Ltd
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
 * Callback for libspotify
 *
 * @param session    The libspotify session
 * @param file_id    The file_id of the file whose size has been found
 * @param size       The file size.
 */
void cb_file_id_info(sp_session *session, sp_file_id file_id, size_t size)
{
  printf("Got file size, file_id=%s, size=%zd\n", file_id, size);
  cmd_done();
}


/**
 *
 */
static void file_size_usage(void)
{
  fprintf(stderr, "Usage: get_file_size [file id]\n");
}

/**
 *
 */
static void file_ids_usage(void)
{
  fprintf(stderr, "Usage: get_file_ids [track link]\n");
}

/**
 *
 */
int cmd_get_file_size(int argc, char **argv)
{
  char *query;

  if (argc < 2) {
    file_size_usage();
    return -1;
  }

  query = argv[1];
  sp_get_file_info(g_session, query);

  return 0;
}

/**
 *
 */
int cmd_get_file_ids(int argc, char **argv)
{
  char *query;
  sp_link *link;
  sp_track *track;

  if (argc < 2) {
    file_ids_usage();
    return -1;
  }

  query = argv[1];

  link = sp_link_create_from_string(query);

  track = NULL;
  if (link) {
    track = sp_link_as_track(link);
    sp_link_release(link);
  }

  if (!track) {
    fprintf(stderr, "Failed to create track object.\n");
    cmd_done();
    return -1;
  }

  if (!sp_track_is_loaded(track)) {
    fprintf(stderr, "Track is not loaded.\n");
    cmd_done();
    return -1;
  }

  sp_file_id fileids[10];
  sp_bitrate bitrates[10];
  size_t size = sizeof(fileids);
  if (sp_track_get_file_ids(track, fileids, bitrates, &size) != SP_ERROR_OK) {
    fprintf(stderr, "Can't get file id.");
  }

  for (int i = 0; i < size; ++i) {
    printf("File id: %s\n", fileids[i]);
    printf("Bitrate: %d\n", bitrates[i]);
  }

  cmd_done();

  return 0;
}
