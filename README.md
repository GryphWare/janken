# janken

🪨✂️📄 Rock-Paper-Scissors Prediction Game (C version)

Description
This is a console-based Rock-Paper-Scissors game with a twist:Instead of just playing one round, the bot plays multiple rounds and tracks outcomes statistically to help you guess the most likely result.

It uses:
A transition matrix to make the bot's choices change probabilistically.
A match-up table to determine win/lose/draw outcomes.
A hint system with randomness to reveal or hide outcome frequencies.
A simulation approach where the Law of Large Numbers helps improve prediction accuracy as you increase rounds.

Features
✅ Simulates the bot's moves for multiple rounds
✅ Shows win/lose/draw rate of the bot
✅ Gives optional hints (randomly)
✅ Helps you guess what the most frequent outcome might be
✅ Uses pseudo-random transitions to mimic learning behavior

How to Play
Select your move:
0 = ROCK
1 = SCISSORS
2 = PAPER

Enter how many rounds you want the bot to simulate.
The bot simulates its move against your fixed choice over many rounds.
You'll be shown a hint (or hidden value) of how often each outcome occurred.
Try to guess what the most frequent outcome was:
0 = WIN (you win)
1 = LOSE (you lose)
2 = DRAW
See if your prediction was correct and view the outcome percentages.
