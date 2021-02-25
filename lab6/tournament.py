# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Initialize teams as an empty list
    teams = []

    # Read teams from file given at command line
    with open(sys.argv[1],'r') as file:
        #Read each line as a dictionary
        lines = csv.DictReader(file)

        # Append to teams list
        for line in lines:
            #Convert rating to int first
            line['rating'] = int(line['rating'])

            #Append
            teams.append(line)



    counts = {}
    for i in range(N):
        #Simulate a tournament and record winner
        winner = simulate_tournament(teams)

        #Update the counts dictionary
        counts[winner] = counts.get(winner,0) + 1 #Use get to avoid invalid key


    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""

    #Get length of the teams list
    length = len(teams)

    #Base case: 1 team left means it's the winner
    if length == 1:
        return teams[0]['team']

    #Otherwise, simulate rounts
    else:
        round_winners = simulate_round(teams)

        #Simulate smaller tournament with remaning teams
        return simulate_tournament(round_winners)


if __name__ == "__main__":
    main()
