function[x] = fibonacci(n)

% Returns a nonzero, nonrepeating fibonacci series of 
% n elements

x = zeros(n,1);
x(1) = 1;
x(2) = 2;

for i=1:n-2
    x(i+2) = x(i) + x(i+1);
end