# MonopolyDeal
Akshay's Fall 2019 project.

(incomplete) C telnet/netcat server that was supposed to help me pass my Honors Chemistry 10 class.

Based off of another (incomplete) similar project I made in the summer of 2019, that would, if completed, emulate the card game "Monopoly Deal".

## Getting Started

#### Installing

Clone the repo, and run the Makefile:

```
git clone https://github.com/SnootierMoon/VeryOld-ChemChat.git
cd VeryOld-ChemChat
make
```

#### Running the server

Unlike the Monopoly Deal server, this just creates an executable called 'out'. The port is 42069.

#### Connecting a client and Other Stuff

Read the instructions from the old [Monopoly Deal README file](https://github.com/SnootierMoon/MonopolyDeal#getting-started).

## Journey

I made this because I thought I would struggle in my 10th grade Honors Chemistry class. I wanted to add so many features: efficient periodic tables, automatic sig fig calculators, etc., but I didn't have enough time. Now it's incomplete, and I honestly don't have the motivation to work on it further. It's a nice showcase of what could have been, and I hope to make a complete server like these in the future.

I learned a lot while making this. I improved so much from the last server: removing dynamic allocations where they weren't needed, making the entire program more scalable. However, I also learned a lot through the mistakes I made in this project. I tried to make the functions and variable names more organized, but they also become more needlessly verbose (so many underscores).

I also learned that a server like this one requires a lot of thought about design. As I added more features and commmands that could all be called at any instant, I noticed that the command names became longer and more inconvenient. I still don't know how I'll solve this issue, but I'm testing a few ideas to use in the future. It's especially hard because it has to work with simple interfaces like netcat/telnet, rather than a GUI, which is a challenge that I deliberately enforced upon myself.

I think a project like this is very helpful for learning because it requires me to think about scalability and design, while still being very simple and intuitive.

## TODO

Finish it.
