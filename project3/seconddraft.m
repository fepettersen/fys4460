close all
clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%------------P(p,L)------------------------------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

L = 10; L2 = L*L;
r = rand(L,L);
step = 0.1; i = 1;
Prob = linspace(0,1,1/step);
p = linspace(step,1,1/step);


parfor i=1:1/step
    z = r<p(i);
    [lw,num] = bwlabel(z,4);
    %img = label2rgb(lw,'jet','r','shuffle');
    %image(img);
    a = intersect(lw(1,:),lw(L,:));
    b = intersect(lw(:,1),lw(:,L));
    u = union(a,b);
    if(max(u) ~=0)
        s = regionprops(lw,'Area');
        %bbox = cat(1,s.BoundingBox);
        area = cat(1,s.Area);
        tmp = area(max(u))/L2;
        Prob(i) =tmp;
    else
        Prob(i) = 0;
    end
end

%plot(p,(Prob));
hold on
x = p(0.6/step:L);
pc = 0.59275;
beta = log(Prob(0.6/step:L))./log(x-pc);

f = polyfit(x,beta,2);
beta = f(1)*x.^2 + f(2)*x +f(3);
%plot(x,(x-pc).^beta,'ro')
%matlabpool('close');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%-------------Finding distribution--------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

z = rand(1e6,1).^(-3+1);
Z = log10(z);
N = zeros(1,100);
p = linspace(0,max(Z));
for i=1:100
    n = Z<p(i);
    N(1,i) = sum(n);
end
N = N/1e6;
plot(p,N)
fit = polyfit(p,N,2);
plot(p,fit(1)*p.^2 +fit(2)*p + fit(3),'ro');