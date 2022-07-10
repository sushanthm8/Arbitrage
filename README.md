# Arbitrage

## What is Arbitrage?
Arbitrage is when you purchase and sell the same assets in different markets in order to profit from minute differences in the prices between markets. 

## Summary
I first got the data from ExchangeRate-API using python and formatted it into a file to be processed in C++. After organizing the data I calculated the conversion rates between each currency. 
<br />
<br />
In order to determine if there is an arbitrage we need to find a cycle where the product of the conversion rates is greater than 1. To make the implementation easier with graphs we take the negative logarithm and if this is negative then there is an arbitrage opportunity.
<br />
<br />
After compiling the conversion rates I performed the Bellman Ford Algorithm. This algorithm is used in general to solve the single-source shortest path. It minimizes the weights from a source vertex. In this project I minimize the distance from a source vertex using the exchange rates. After iterating through all of the data once we do it one more time. If there continues to be any negative cycles we have found some opportunities which are stored and printed out.
