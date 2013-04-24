close all
clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%------------P(p,L)------------------------------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% L = 200;
L = [25,50,100,200,400,800];
step = 0.001; i = 1;
Prob = zeros(1/step,length(L));
p = [linspace(0,0.44,10),linspace(0.45,0.70,1500),linspace(0.71,1.0,10)];
experiments = 750;
Pi = zeros(1/step,length(L));
for matrices = 1:length(L)
    tic
    L2 = L(matrices)*L(matrices);
    matrices
    for i=1:length(p)
        for j=1:experiments
            r = rand(L(matrices),L(matrices));
            z = r<p(i);
            [lw,num] = bwlabel(z,4);    
            %img = label2rgb(lw,'jet','r','shuffle');
            %image(img);
            a = intersect(lw(1,:),lw(L(matrices),:));
            b = intersect(lw(:,1),lw(:,L(matrices)));
            u = union(a,b);
            if(max(u) ~=0)
                Pi(i,matrices) = Pi(i,matrices) +1;
                s = regionprops(lw,'Area');
                area = cat(1,s.Area);
                tmp = area(max(u))/L2;
                Prob(i,matrices) =tmp;
            else
                Prob(i,matrices) = 0;
            end
        end
        Pi(i,matrices) = Pi(i,matrices)/experiments;
    end
    toc
end

plot(p,Pi);
hold on
% x = p(0.6/step:L);
% pc = 0.59275;
% beta = log(Prob(0.6/step:L))./log(x-pc);
% 
% f = polyfit(x,beta,2);
% beta = f(1)*x.^2 + f(2)*x +f(3);
%plot(x,(x-pc).^beta,'ro')
%plot(x,(x-pc).^(0.5),'gx')
%matlabpool('close');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%-------------Finding distribution--------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% z = rand(1e6,1).^(-2);
% p = exp(linspace(0,log(max(z)),400));
% N = zeros(1,length(p));
% for i=1:length(p)
%     n = z>p(i);
%     N(1,i) = sum(n);
% end
% N = N/1e6;

% plot(log(p),log(N));
% ylabel('log(P(Z>z))');
% xlabel('log(Z)');
% figure()
% plot(log(p),N)
% legend('')
% hold on
% plot(log(p),(p).^(-1.0/2.0),'ro');
% legend('measurment','model')
% xlabel('log(Z)');

