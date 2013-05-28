close all
clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%------------P(p,L)------------------------------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

N = 400;
% L = 200;
L = [25,50,100,200,400,800];
step = 0.001; i = 1;
Prob = zeros(N+6,length(L));
% p = [linspace(0,0.44,10),linspace(0.45,0.70,150),linspace(0.71,1.0,10)];
p = zeros(length(L),N+6);
experiments = 500;
Pi = zeros(N+6,length(L));
pc = 0.59275;


for matrices = 1:length(L)
    tic
    lx = L(matrices);
    L2 = lx*lx;
    %p(matrices,:) = [linspace(0.1,pc-6/L(matrices),3),linspace(pc-6/L(matrices),pc+6/L(matrices),N),linspace(pc+6/L(matrices),1,3)];
    p(matrices,:) = linspace(0,1,N+6);
    matrices
    for i=1:length(p)
        for j=1:experiments
            r = rand(lx,lx);
            z = r<p(matrices,i);
            [lw,num] = bwlabel(z,4);   
            %img = label2rgb(lw,'jet','r','shuffle');
            %image(img);
             perc_x = intersect(lw(1,:),lw(lx,:));
             perc_y = intersect(lw(:,1),lw(:,lx));
             perc = perc_x(perc_x~=0);
            if(isempty(perc) ~=1)
                Pi(i,matrices) = Pi(i,matrices) +1;
%                 s = regionprops(lw,'Area');
%                 area = cat(1,s.Area);
                tmp = sum(sum(lw==perc(1)))/L2;
                Prob(i,matrices) = Prob(i,matrices) +tmp;
            else
                Prob(i,matrices) = Prob(i,matrices) + 0;
            end
        end
        Pi(i,matrices) = Pi(i,matrices)/experiments;
         Prob(i,matrices) =  Prob(i,matrices)/experiments;
    end
    toc
end

hold all
leg = {};
for i=1:length(L)
    plot(p(i,:),Prob(:,i));
    leg{i} = sprintf('L = %d',L(i));
end
legend(leg,2)
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

