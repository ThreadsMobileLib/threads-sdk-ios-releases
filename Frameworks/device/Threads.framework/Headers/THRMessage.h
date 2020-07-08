//
//  THRMessage.h
//  Threads
//
//  Created by Nikolay Kagala on 01/06/16.
//  Copyright © 2016 Sequenia. All rights reserved.
//

#import "THRObject.h"
#import <UIKit/UIKit.h>
#import "THRParticipant.h"

@class QuickReply;
@class OpenGraphData;

typedef NS_ENUM(NSUInteger, THRMessageStatus) {
    THRMessageStatusPending,
    THRMessageStatusSent,
    THRMessageStatusDelivered,
    THRMessageStatusRead,
    THRMessageStatusFailed
};

@protocol JSQMessageMediaData;

@interface THRMessage : THRObject <NSCopying>

/**
 *  The `THRMessage` class is a copy of `JSQMessage` 
 *
 *  `JSQMessage`class is a concrete class for message model objects that represents a single user message.
 *  The message can be a text message or media message, depending on how it is initialized.
 *  It implements the `THRMessageData` protocol and it contains the senderId, senderDisplayName,
 *  and the date that the message was sent. If initialized as a media message it also contains a media attachment,
 *  otherwise it contains the message text.
 */

/**
 *  Unique message identifier
 */
@property (copy, nonatomic, readwrite) NSString *uuid;

/**
 * MessageId in MFMS system, required to mark messages as read
 */
@property (nonatomic, readwrite) NSMutableArray<NSString*>* providerIds;

/**
 *  Returns the object of `THRParticipant`. It is the user who sent the message.
 */
@property (copy, nonatomic, readonly) THRParticipant *author;

/**
 *  Returns the date that the message was sent.
 */
@property (copy, nonatomic, readwrite) NSDate *date;

/**
 *  Returns a boolean value specifying whether or not the message contains media.
 *  If `NO`, the message contains text. If `YES`, the message contains media.
 *  The value of this property depends on how the object was initialized.
 */
@property (assign, nonatomic, readonly) BOOL isMediaMessage;

/**
 *  Returns the body text of the message, or `nil` if the message is a media message.
 *  That is, if `isMediaMessage` is equal to `YES` then this value will be `nil`.
 */
@property (copy, nonatomic, readonly) NSString *text;

@property (copy, nonatomic, readonly) NSString *formattedText;

@property (nonatomic, readwrite) OpenGraphData* ogData;
@property (nonatomic, readwrite) NSURL* ogUrl;
@property (nonatomic, readwrite) BOOL ogLoading;
@property (nonatomic, readwrite) UIImage* ogImage;

/**
 *  Returns the media item attachment of the message, or `nil` if the message is not a media message.
 *  That is, if `isMediaMessage` is equal to `NO` then this value will be `nil`.
 */
@property (copy, nonatomic, readwrite) id<JSQMessageMediaData> media;

/**
 *  Returns the current status of the message
 */
@property (assign, nonatomic, readwrite) THRMessageStatus status;

/**
 *  Returns the quoted message. Nil if current message isn't quote.
 */
@property (strong, nonatomic, readwrite) THRMessage* quotedMessage;

@property (nonatomic, readwrite) NSArray<QuickReply*>* quickReplies;

@property (nonatomic, readwrite) BOOL isQuickReply;
/**
 *  Returns YES if current message is system message `N new nessages`.
 */
@property (nonatomic, readwrite) BOOL isUnreadCounter;

/**
 *  Returns YES if current message was loaded from history.
 */
@property (nonatomic, readwrite) BOOL loadedFromHistory;

/**
 *  Returns the formatted date. Uses for message header
 */
- (NSString*)dayHeader;

/**
 *  @return the image according to current status of the message, or nil
 */
- (UIImage*) statusImage;

- (UIColor*) statusColor;

- (NSUInteger)messageHash;

- (NSString*)sentDateDescription;

- (BOOL)isFileMessage;

- (BOOL) isSystemMessage;

- (NSDictionary *)toDictionary;

- (BOOL) containsOGData;

- (NSString *)hashWithoutDate;

- (NSUInteger)hashWithStatus;

- (NSUInteger)sizableDataHash;

- (void) changeDateTo: (NSDate *) date;

- (void) addProviderId: (NSString*) providerId;

#pragma mark - Initialization

//TODO: description for functions

/**
 *  Initializes and returns a message object having the given senderId, displayName, text,
 *  and current system date.
 *
 *  @param senderId    The unique identifier for the user who sent the message. This value must not be `nil`.
 *  @param displayName The display name for the user who sent the message. This value must not be `nil`.
 *  @param text        The body text of the message. This value must not be `nil`.
 *
 *  @discussion Initializing a `THRMessage` with this method will set `isMediaMessage` to `NO`.
 *
 *  @return An initialized `THRMessage` object if successful, `nil` otherwise.
 */
+ (instancetype)messageWithAuthor:(THRParticipant*) author
                             text:(NSString*) text
                    formattedText:(NSString*) formattedText;

+ (instancetype)messageWithAuthor:(THRParticipant*) author
                             date:(NSDate*) date
                             text:(NSString*) text
                    formattedText:(NSString*) formattedText;

/**
 *  Initializes and returns a message object having the given senderId, senderDisplayName, date, and text.
 *
 *  @param senderId          The unique identifier for the user who sent the message. This value must not be `nil`.
 *  @param senderDisplayName The display name for the user who sent the message. This value must not be `nil`.
 *  @param date              The date that the message was sent. This value must not be `nil`.
 *  @param text              The body text of the message. This value must not be `nil`.
 *
 *  @discussion Initializing a `THRMessage` with this method will set `isMediaMessage` to `NO`.
 *
 *  @return An initialized `THRMessage` object if successful, `nil` otherwise.
 */
- (instancetype)initWithAuthor:(THRParticipant*) author
                          date:(NSDate*) date
                          text:(NSString*) text
                 formattedText:(NSString*) formattedText;

+ (instancetype)messageWithAuthor: (THRParticipant*) author
                             date: (NSDate*) date
                             text: (NSString*) text
                    formattedText: (NSString*) formattedText
                            media: (id<JSQMessageMediaData>) media;
/**
 *  Initializes and returns a message object having the given senderId, displayName, media,
 *  and current system date.
 *
 *  @param senderId    The unique identifier for the user who sent the message. This value must not be `nil`.
 *  @param displayName The display name for the user who sent the message. This value must not be `nil`.
 *  @param media       The media data for the message. This value must not be `nil`.
 *
 *  @discussion Initializing a `THRMessage` with this method will set `isMediaMessage` to `YES`.
 *
 *  @return An initialized `THRMessage` object if successful, `nil` otherwise.
 */
+ (instancetype)messageWithAuthor:(THRParticipant *)author
                            media:(id<JSQMessageMediaData>)media;

+ (instancetype)messageWithAuthor:(THRParticipant *)author
                             date:(NSDate *)date
                            media:(id<JSQMessageMediaData>)media;

/**
 *  Initializes and returns a message object having the given senderId, displayName, date, and media.
 *
 *  @param senderId          The unique identifier for the user who sent the message. This value must not be `nil`.
 *  @param senderDisplayName The display name for the user who sent the message. This value must not be `nil`.
 *  @param date              The date that the message was sent. This value must not be `nil`.
 *  @param media             The media data for the message. This value must not be `nil`.
 *
 *  @discussion Initializing a `THRMessage` with this method will set `isMediaMessage` to `YES`.
 *
 *  @return An initialized `THRMessage` object if successful, `nil` otherwise.
 */
- (instancetype)initWithAuthor:(THRParticipant *)author
                          date:(NSDate *)date
                         media:(id<JSQMessageMediaData>)media;
/**
 *  Initializes and returns a message object from NSDictionary.
 *
 *  @param dict     NSDictionary with properties of message
 *
 *  @return An initialized `THRMessage` object if successful, `nil` otherwise.
 */
- (instancetype)initWithJSON:(NSDictionary *)dict;

/**
 *  Initializes and returns a message object from other message that was encode from coder.
 *
 *  @return An initialized `THRMessage` object.
 */
+ (instancetype)messageWithMessage: (THRMessage *) message;


@end
