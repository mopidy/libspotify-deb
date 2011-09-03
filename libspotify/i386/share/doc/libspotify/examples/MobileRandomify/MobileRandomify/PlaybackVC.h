//
//  PlaybackVC.h
//  MobileRandomify
//
//  Created by Joachim Bengtsson on 2011-08-04.
//  Copyright 2011 Spotify AB. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SpotifySession;

@interface PlaybackVC : UIViewController
@property(nonatomic,retain) IBOutlet UILabel *trackName;
@property(nonatomic,retain) IBOutlet UILabel *artistName;
@property(nonatomic,retain) IBOutlet UILabel *status;
@property(nonatomic,retain) IBOutlet UIButton *pause, *skip;
@property(nonatomic,readonly) BOOL playing;

-(id)initWithSession:(SpotifySession*)sess;
-(IBAction)skipToNextTrack:(id)sender;
-(IBAction)togglePlaying:(id)sender;
-(void)playingStopped;

// forwarded from appdelegate
-(void)sessionUpdatedMetadata:(SpotifySession *)session_;
@end
