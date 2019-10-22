# MCS
Simulation X
This is a simulation framework for carrying out metropolis monte calo simulations of Patchy Spherocylinders.
The project is under continuous development.

Compile via: g++ -std=c++11 main2.cpp runparam.cpp initial.cpp updator.cpp  -o SimX

Run: ./SimX <Parameter Parameter_Value>

Parameter List:

* RunID Parameters - Generates a unique token for the run for bookkeping purposes.

  - "set" <int> #Sets the counter to the desired 
  - "reset" #Resets the counter to zero
  - "noincrement" #Does not increment the RunID, instead adds 0.1 to the current RunID
  - <No arg passed> #Current RunID incremented by 1 compared to the previous one
  
 
* "particles": Number of particles in the box
* "sweeps": Number of total trial moves to be conducted
* "checkpoints": Number of times an XYZ trajectory file is generated for all particles in the box. The checkpoints are evenly distributed w.r.t to the total sweeps
"threads": Number of parallel threads that would run the same simulation box.

Eg: ./SimX sweeps 1000 particles 1000 checkpoints 5

RunID: 10 (default: -1)
Sweeps: 1000 (default: 1000)
Checkpoint: 5 (default: 1)
Threads: 1 (default: 1)
Particles in Box: 1000 (default: 100)




Notes: 
1. The parameters can be entered in any order.
2. Additional parameters can be modified in "runparam.cpp".
3. Sudo access is recommended for running the Simulation.
