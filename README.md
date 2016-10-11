# Integration-Monte-Carlo
The realization of Monte-Carlo method of integration. Includes non-parallel and parallel implementation.

# Результаты работы
## Обычный метод. Интеграл x^2. 

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.8971200000
Working time = 1.97434

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.7269600000
Working time = 1.92094

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.7693600000
Working time = 1.81124

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.0524000000
Working time = 1.81906

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.3848800000
Working time = 1.84193

##MPI Алгоритм. Интеграл x^2. 

###запуск mpiexec -n 10

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.7250400000
Working time = 0.8083

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.7489600000
Working time = 0.7899

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.3560800000
Working time = 0.5968

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2665.9069600000
Working time = 0.7257

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.2595200000
Working time = 0.7296


###запуск mpiexec -n 100

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.4209600000
Working time = 0.7874

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.6608800000
Working time = 0.6985

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.8268000000
Working time = 0.7264

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.7660000000
Working time = 0.7104

a=0, b=20, stepM=10, amountofDot=100000000
Integral = 2666.5212000000
Working time = 0.8296
