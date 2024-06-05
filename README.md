# FT_IRC 

IRC (Internet Relay Chat) is a **protocol for real-time text messaging between internet-connected computers created in 1988**. It is mainly used for group discussion in chat rooms called “channels” although it supports private messages between two users, data transfer, and various server-side and client-side commands. As of April 2011, the top 100 IRC networks served over 500,000 users at a time on hundreds of thousands of channels.

| COMMAND | DESCRIPTION |
| --- | --- |
| Join | The JOIN command indicates that the client wants to join the given channel(s), each channel using the given key for it. |
| Kick | The KICK command can be used to request the forced removal of a user from a channel. This command can only be used by the channel's administrator. |
| Privmsg | The PRIVMSG command is used to send private messages between users, as well as to send messages to channels. |
| Quit | The QUIT command is used to terminate a client’s connection to the server.  |
| Topic | The TOPIC command is used to modify or view the topic of the specified channel. This command can only be used by the channel's administrator. |
| Notice | The NOTICE command is used to send notices between users, as well as to send notices to channels. The difference between NOTICE and PRIVMSG is that automatic replies must never be sent in response to a NOTICE message. |
| Nick | The NICK command is used to give the client a nickname or change the previous one. |
| User | The USER command is used at the beginning of a connection to specify the username and realname of a new user. |
| Part | The PART command removes the client from the given channel(s). |
| Who | The WHO command shows who is in the channel entered as a parameter. |
| Pass | The PASS command compares a new user's password with the server's password and if it is correct, it successfully connects to the server. |

<p align="center"> <img src=["assets/network.png"](https://github.com/faruktinaz/ft_irc/assets/114104599/c58afdef-3d2a-4b50-966e-bb97332a5a13)> </p>
