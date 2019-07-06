from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""

    cost = [[(0, None) for x in range(len(b)+1)] for y in range(len(a) +1)]

    cost[0][0] = (0, None)

    for i in range(1, len(a) + 1):
        cost[i][0] = (i, Operation.DELETED)
    for j in range(1, len(b) + 1):
        cost[0][j] = (j, Operation.INSERTED)


    for i in range(1, len(a)+1):
        for j in range(1, len(b)+1):

            #print("")
            #print(cost)
            #print(i)
            #print(j)
            #print("")

            delete = cost[i-1][j][0] + 1
            insert = cost[i][j-1][0] + 1

            if (a[i-1] == b[j-1]):
                sub = cost[i-1][j-1][0]
            else:
                sub = cost[i-1][j-1][0] + 1

            mincost = min(delete, insert, sub)

            if mincost == delete:
                operation = Operation.DELETED
            if mincost == insert:
                operation = Operation.INSERTED
            if mincost == sub:
                operation = Operation.SUBSTITUTED

            cost[i][j] = (mincost, operation)
    print (cost)
    return cost
