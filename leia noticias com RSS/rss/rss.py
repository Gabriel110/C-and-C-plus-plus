import feedparser
import sys 
import re
import getopt
import string 


try:
  opts, args = getopt.getopt(sys.argv[1:], "uh", ["urls", "help"])
except:
  print('erro')
include_urls = False
for o, a in opts:
    if o == "-u":
        include_urls = True
    elif o in ("-h", "--help"):
        usage()
        sys.exit()
    else:
        assert False, "unhandled option"


def newFeed(feed):
  NewsFeed = feedparser.parse(feed)
  #print("+++++++++++++++++++++++++ NEW FEED ++++++++++++++++++++++++++++++++++++++++++++++")
  #print('Numero de RSS postados :', len(NewsFeed.entries))
  #entry = NewsFeed.entries[1]
  #print(entry.keys())
  #print('Titulo do pos: {0}'.format(entry.title))
  #print('Data: {0}'.format(entry.published))
  #print('Sumario:{0}'.format(entry.summary_detail))
  #print('Link: {0}\n'.format(entry.link))
  print('{0}'.format(entry.link))



newFeed(args[0])