#include <iostream>


short n, m;  // Size
short table[100][100];  // Table

// Point structure (contain X and Y coord)
struct Point {
    int x;
    int y;
};


Point used[128], found[128];  // Point stacks
short usedNumber = 0, foundNumber = 0;  // Point stack's index


void printTable() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    Point startPoint, exitPoint;  // Start & exit points
    short step = 0;  // Step counter
    bool isFound = false;  // Do exit found or not

    // Sizes input
    std::cout << "Enter n, m:";
    std::cin >> n >> m;

    // Table input
    std::cout << "Enter table:" << std::endl;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> table[i][j];
        }
    }

    // Start point input
    std::cout << "Enter x, y:";
    std::cin >> startPoint.x >> startPoint.y;

    // Add start point to 'used' stack
    used[usedNumber] = startPoint;
    usedNumber++;

    // Mark table point that is used already
    table[startPoint.y - 1][startPoint.x - 1] = 2;

    // Check if start point is exit
    if (startPoint.x == 1 || startPoint.x == n || startPoint.y == 1 || startPoint.y == m) {
        std::cout << startPoint.x << " " << startPoint.y << std::endl;
        return 0;
    }

    // BFS path searching
    while (usedNumber) {
        foundNumber = 0;  // Clear 'found' stack
        step++;  // Next step

        // Iterate through previously found points
        for (int pointNumber = 0; pointNumber < usedNumber; pointNumber++) {
            Point current = used[pointNumber];  // Assign current point

            if (current.x > 1) {  // Is point at the left side
                if (table[current.y - 1][current.x - 2] == 0) {  // Is there an exit left to point
                    found[foundNumber].x = current.x - 1;
                    found[foundNumber].y = current.y;

                    foundNumber++;

                    table[current.y - 1][current.x - 2] = step + 2;
                }
            }

            if (current.x < n) {  // Is point at the right side
                if (table[current.y - 1][current.x] == 0) {  // Is there an exit right to point
                    found[foundNumber].x = current.x + 1;
                    found[foundNumber].y = current.y;

                    foundNumber++;

                    table[current.y - 1][current.x] = step + 2;
                }
            }

            if (current.y > 1) {  // Is point at the top side
                if (table[current.y - 2][current.x - 1] == 0) {  // Is there an exit above a point
                    found[foundNumber].x = current.x;
                    found[foundNumber].y = current.y - 1;

                    foundNumber++;

                    table[current.y - 2][current.x - 1] = step + 2;
                }
            }

            if (current.y < m) {  // Is point at the bottom side
                if (table[current.y][current.x - 1] == 0) {  // Is there an exit below a point
                    found[foundNumber].x = current.x;
                    found[foundNumber].y = current.y + 1;

                    foundNumber++;

                    table[current.y][current.x - 1] = step + 2;
                }
            }
        }

        usedNumber = 0;  // Clear 'used' stack

        // Iterate through found points
        for (int pointNumber = 0; pointNumber < foundNumber; pointNumber++) {

            // Check if any of points is exit
            if (found[pointNumber].x == 1 || found[pointNumber].x == n || found[pointNumber].y == 1 || found[pointNumber].y == m) {
                exitPoint = found[pointNumber];  // Assign exit point
                isFound = true;
                break;
            }

            // If none of points is exit, write it to 'used' stack and repeat
            used[pointNumber] = found[pointNumber];
            usedNumber++;
        }

        // If found exit, then break
        if (isFound) {
            break;
        }
    }


    if (!isFound) {  // If exit not found
        std::cout << "NO";
    }
    else {  // If exit found
        printTable(); // Print result table

        const int steps = step + 1;
        Point path[steps];  // Create array for path points

        path[step] = exitPoint;  // Add exit point to path
        step--;

        // Add previous points to path
        while (step >= 0) {
            Point current = path[step + 1];

            // Check if previous point is left side
            if (current.x > 1) {
                if (table[current.y - 1][current.x - 2] == step + 2) {
                    path[step].x = current.x - 1;
                    path[step].y = current.y;
                    step--;
                    continue;
                }
            }

            // Check if previous point is on right side
            if (current.x < n) {
                if (table[current.y - 1][current.x] == step + 2) {
                    path[step].x = current.x + 1;
                    path[step].y = current.y;
                    step--;
                    continue;
                }
            }

            // Check if previous point is below
            if (current.y > 1) {
                if (table[current.y - 2][current.x - 1] == step + 2) {
                    path[step].x = current.x;
                    path[step].y = current.y - 1;
                    step--;
                    continue;
                }
            }

            // Check if previous point is above
            if (current.y < m) {
                if (table[current.y][current.x - 1] == step + 2) {
                    path[step].x = current.x;
                    path[step].y = current.y + 1;
                    step--;
                    continue;
                }
            }

        }

        // Output path array
        for (int pointNumber = 0; pointNumber < steps; pointNumber++) {
            std::cout << path[pointNumber].x << " " << path[pointNumber].y << std::endl;
        }
    }
}