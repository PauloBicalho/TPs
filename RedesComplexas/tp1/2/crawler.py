import tweepy
import time
import sys


def check_limit( api, name1, name2 ):
  status = api.rate_limit_status()
  rest = int(status['resources'][name1][name2]['remaining'])

  if( rest <= 0 ):
    sleep_time = float(status['resources'][name1][name2]['reset']) - time.time() + 10
    print >> sys.stderr, "\nTwitter rate limit exceeded... Sleeping\n"
    if(sleep_time > 0):
      time.sleep(sleep_time)
  
    check_limit( api, name1, name2 )
  
  return rest


def get_tweets(api, user_id):
  c = tweepy.Cursor(api.user_timeline, id = user_id, count=200) 

  rest = check_limit( api, 'statuses', '/statuses/user_timeline' )

  total = 0
  for page in c.pages():
    for t in page:
      print t.text.encode('utf8')
      total += 1

    rest -= 1
    if( rest <= 0 ):
      rest = check_limit( api, 'statuses', '/statuses/user_timeline' )

  print "\nTotal: %s" % total


def get_followers(api,user_id):
  c = tweepy.Cursor(api.followers, id = user_id, count=200)

  rest = check_limit( api, 'followers', '/followers/list' )

  total = 0
  for page in c.pages():
    for u in page:
      print u.id
      total += 1

    rest -= 1
    if( rest <= 0 ):
      rest = check_limit( api, 'followers', '/followers/list' )

  print "\nTotal: %s" % total

def get_following(api,user_id):
  c = tweepy.Cursor(api.friends, id = user_id, count=200)

  rest = check_limit( api, 'friends', '/friends/list' )

  total = 0
  for page in c.pages():
    for u in page:
      print u.id
      total += 1

    rest -= 1
    if( rest <= 0 ):
      rest = check_limit( api, 'friends', '/friends/list' )
  
  print "\nTotal: %s" % total

def main(user_id):
  consumer_key = "Ldwx2Oyhnq6FSMzoUZ7S8g"
  consumer_secret = "U7od6oa1QhgN1QaNxg8YFI3kbwQoBqL2i3OyKQe0Tc"
  access_token = "258943694-6s5OsAuwkJb1xCiwfBi6MiVRNERLYiwB9Rn0SIpF"
  access_token_secret = "VASkbolBNB1Uc0lmMb9avD89QNl1rxQvXrEHx6KIXOSN7"

  auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
  auth.set_access_token(access_token, access_token_secret)

  api = tweepy.API(auth)
  user = api.get_user(user_id)

#  print "\n----------- Retrieving tweets -------------\n"
 # tweets = get_tweets(api, user_id)
  
  print "\n----------- Retrieving followers ----------\n"
  followers = get_followers(api, user_id)
  
  print "\n----------- Retrieving following ----------\n"
  following = get_following(api, user_id)


  # If the authentication was successful, you should
  # see the name of the account print out



  # If the application settings are set for "Read and Write" then
  # this line should tweet out the message to your account's 
  # timeline. The "Read and Write" setting is on https://dev.twitter.com/apps
 # api.update_status('Updating using OAuth authentication via Tweepy!')





if __name__ == '__main__':
  user_id = int(sys.argv[1])
  main(user_id)
