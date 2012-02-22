//
//  PlaybackVC.m
//  MobileRandomify
//
//  Created by Joachim Bengtsson on 2011-08-04.
//  Copyright 2011 Spotify AB. All rights reserved.
//

#import "PlaybackVC.h"
#import "SpotifySession.h"

@interface PlaybackVC () <SpotifyPlaylistDelegate>
@property(nonatomic,retain) SpotifySession *session;
@property(nonatomic,retain) SpotifyPlaylist *starred;
@property(nonatomic,readwrite) BOOL playing;
@property(nonatomic,retain) SpotifyTrack *playingTrack;
@end

@implementation PlaybackVC
@synthesize trackName = _trackName, artistName = _artistName, status = _status;
@synthesize pause = _pause, skip = _skip;
@synthesize session = _session, starred = _starred;
@synthesize playing = _playing, playingTrack = _playingTrack;

-(id)initWithSession:(SpotifySession*)sess;
{
	if(![super initWithNibName:NSStringFromClass([self class]) bundle:nil]) return nil;
	self.title = @"Playback";
	self.status.text = @"Starting up...";
	self.session = sess;
	self.starred = sess.starred;
	self.starred.delegate = self;
	
	return self;
}
-(void)dealloc;
{
	self.trackName = self.artistName = self.status = nil;
	self.pause = self.skip = (id)nil;
	self.session = nil;
	self.starred = nil;
	self.playingTrack = nil;
	[super dealloc];
}
-(void)viewDidLoad;
{
	[super viewDidLoad];
	self.playing = NO;
	self.playingTrack = nil;
	[self skipToNextTrack:nil];
}
-(void)viewWillDisappear:(BOOL)animated;
{
	[super viewDidDisappear:animated];
	// Pressing 'back' goes back to login screen
	[self.session logout];
}

-(IBAction)skipToNextTrack:(id)sender;
{
	NSUInteger count = [_starred countOfTracks];

	if(!_starred.loaded || !count) {
		self.status.text = @"Waiting for playlist to load...";
		return;
	}
	
	NSUInteger randomIndex = random()%count;
	
	self.playingTrack = [_starred objectInTracksAtIndex:randomIndex];
	if(!self.playingTrack.loaded) {
		self.status.text = @"Waiting for track to load...";
		return;
	}
	
	self.status.text = [NSString stringWithFormat:@"Playing track %@", _playingTrack];
	
	[_session loadTrack:_playingTrack];
	[_session play];

	self.playing = YES;
}
-(IBAction)togglePlaying:(id)sender;
{
	if(_playing) {
		[_session pause];
		self.playing = NO;
	} else {
		[_session play];
		self.playing = YES;
	}
}
-(void)playingStopped;
{
	self.playing = NO;
}

-(void)setPlaying:(BOOL)playing;
{
	_playing = playing;
	self.pause.enabled = _playingTrack != nil;
	self.pause.selected = _playing;
}
-(void)setPlayingTrack:(SpotifyTrack*)track;
{
	[track retain];
	[_playingTrack release];
	_playingTrack = track;
	self.artistName.text = track ? track.artistName : @"(Not playing)";
	self.trackName.text = track ? track.name : @"(Not playing)";
}

-(void)playlistEndedUpdating:(SpotifyPlaylist*)playlist;
{
	if(playlist.loaded && !_playing)
		[self skipToNextTrack:nil];
}
-(void)playlistChangedState:(SpotifyPlaylist*)playlist;
{
	if(playlist.loaded && !_playing)
		[self skipToNextTrack:nil];
}

-(void)sessionUpdatedMetadata:(SpotifySession *)session_;
{
	// A track we're waiting for metadata for might now have gotten it.
	if(!_playing && _playingTrack && _playingTrack.loaded) {
		if(!_playingTrack.available) {
			[self skipToNextTrack:nil];
			return;
		}
		self.status.text = [NSString stringWithFormat:@"Playing now loaded track %@", _playingTrack];
		[_session loadTrack:_playingTrack];
		[_session play];
		self.playing = YES;
	}
}


@end