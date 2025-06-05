Key Features Adaptation for Dog Shelter Simulation:
Dog Types and Priorities:

Dogs are categorized into Dangerous (D), Unwell (U), and Well (W), with corresponding priorities (D=3, U=2, W=1). These will help in prioritizing dog placement in the shelter.

These categories will be tied to the insertion function, where a dog is placed in the tree according to its name, but the priority will also determine its urgency for placement into a cage.

Cage Management:

A fixed number of cages will be simulated.

Each dog is assigned a cage based on its priority, ensuring that higher-priority dogs are placed first. Once a dog is placed, we can track how often a cage is used.

Random Dog Data Generation:

The program will generate random data for dogs, including:

Type (Dangerous, Unwell, Well)

Arrival time

Service time

Cage assignment based on priority

Statistics Tracking:

Total waiting time: How long all dogs have to wait in the shelter before being assigned to a cage.

Cage usage: Track how many times each cage is used.

Dog type summary: The total number of each type of dog (Dangerous, Unwell, Well) admitted to the shelter.

Waiting times for each dog: The total time a dog waits before being placed.

Program Flow Breakdown:
Dog Data Creation:

The program will accept inputs like the number of dogs, number of cages, and other time constraints.

The data will be generated for each dog, including:

Type (Dangerous, Unwell, Well)

Random arrival time (simulated by random generation within a given time range)

Random service time (for when they will be treated or processed)

Dog Placement in Shelters:

The dogs will be inserted into the AVL tree based on their name and priority.

If the dog has the same name as another, it will be placed in the same tree node.

Cage and Dog Management:

After the AVL tree is built, the program will manage the cage availability.

For each dog, the program will check available cages based on their priority and time of arrival.

The priority system will ensure Dangerous dogs (highest priority) are given the first available cages.

Reporting:

Total Waiting Time: Sum of waiting times for all dogs before they are placed in a cage.

Cage Usage: Track how many times each cage has been used.

Dog Type Summary: Report how many Dangerous, Unwell, and Well dogs were admitted and served.

Dog Statistics: For each dog, report detailed statistics such as waiting time and whether the dog’s priority affected its placement in the shelter.
