//
//  MobileRandomifyAppDelegate.m
//  MobileRandomify
//
//  Created by Joachim Bengtsson on 2011-08-03.
//  Copyright 2011 Spotify AB. All rights reserved.
//

#import "MobileRandomifyAppDelegate.h"
#import "SpotifySession.h"
#import "LoginVC.h"
#import "PlaybackVC.h"
#import <AVFoundation/AVFoundation.h>

@interface MobileRandomifyAppDelegate () <SpotifySessionDelegate>
@property(nonatomic,retain) SpotifySession *session;
@property(nonatomic,retain) PlaybackVC *playbackVC;
@property(nonatomic) BOOL wasPlayingBeforeInterruption;
@end

@implementation MobileRandomifyAppDelegate
@synthesize session = _session, loginVC = _loginVC, playbackVC = _playbackVC;
@synthesize window = _window, wasPlayingBeforeInterruption = _wasPlayingBeforeInterruption;
@synthesize navigationController = _navigationController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	self.window.rootViewController = self.navigationController;
	[self.window makeKeyAndVisible];
	
	self.loginVC.appDelegate = self;
	
	NSError *err = nil;
	self.session = [[[SpotifySession alloc] initError:&err] autorelease];
	self.session.delegate = self;
	
	if(!_session) {
		// I'll just leak these, it's a sample project anyway :P
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Couldn't load Spotify" message:[err localizedDescription] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
		[alert show];
	}
	
	[[AVAudioSession sharedInstance] setDelegate:self];
	BOOL success = YES;
	success &= [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback error:&err];
	success &= [[AVAudioSession sharedInstance] setActive:YES error:&err];
	if(!success)
		NSLog(@"Failed to activate audio session: %@", err);
	
	NSLog(@"Finished launching");

    return YES;
}

- (void)dealloc
{
	[_window release];
	[_navigationController release];
	self.session.delegate = nil;
	self.session = nil;
    [super dealloc];
}

-(void)loginWithUsername:(NSString*)user password:(NSString*)pass;
{
	[_session loginUser:user password:pass];
}

#pragma mark Session callbacks
-(void)session:(SpotifySession*)session_ logged:(NSString*)logmsg;
{
	NSLog(@"Spotify: %@", logmsg);
/*	NSString *new = [logmsg stringByAppendingString:log.stringValue];
	log.stringValue = new;*/
}
-(void)sessionLoggedIn:(SpotifySession*)session_ error:(NSError*)err;
{
	if(err) {
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Couldn't log in" message:[err localizedDescription] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
		[alert show];
		return;
	}
	
	self.playbackVC = [[[PlaybackVC alloc] initWithSession:self.session] autorelease];
	
	[self.navigationController pushViewController:_playbackVC animated:YES];
}
-(void)session:(SpotifySession*)session_ connectionError:(NSError*)err;
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Connection error" message:[err localizedDescription] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
}
-(void)session:(SpotifySession*)session_ streamingError:(NSError*)err;
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Streaming error" message:[err localizedDescription] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
}


-(void)sessionUpdatedMetadata:(SpotifySession *)session_;
{
	[self.playbackVC sessionUpdatedMetadata:session_];
}
-(void)sessionEndedPlayingTrack:(SpotifySession*)session_;
{
	[self.playbackVC playingStopped];
	[self.playbackVC skipToNextTrack:nil];
}
-(void)sessionLostPlayToken:(SpotifySession *)session;
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Lost play token" message:@"That means another client is playing music with this account, so this one'll have to stop playing." delegate:nil cancelButtonTitle:@"Arrrrggghhh! My music!" otherButtonTitles:nil];
	[alert show];
	[self.playbackVC playingStopped];
}

- (void)beginInterruption;
{
	_wasPlayingBeforeInterruption = self.playbackVC.playing;
	if(_wasPlayingBeforeInterruption)
		[self.playbackVC togglePlaying:nil];
}
- (void)endInterruptionWithFlags:(NSUInteger)flags NS_AVAILABLE_IPHONE(4_0);
{
	if(_wasPlayingBeforeInterruption && !self.playbackVC.playing && flags & AVAudioSessionInterruptionFlags_ShouldResume)
		[self.playbackVC togglePlaying:nil];
}

@end
