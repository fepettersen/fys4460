%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%-----------Cluster number density---------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all
close all

% logbins = exp(linspace(0,max(lw)));
N = 11;
pc = 0.59275;
L = 1000; L2 = L*L;
r = rand(L,L);
%p = linspace(0.51,pc,N);
p = linspace(pc,pc+0.15,N);
n = zeros(N,N);
s = 2.^(0:N-1);

% parfor i=1:N
%     z = r<p(i);
%     [lw,num] = bwlabel(z,4);
%     a = intersect(lw(1,:),lw(L,:));
%     b = intersect(lw(:,1),lw(:,L));
%     u = union(a,b);
%     tmp = regionprops(lw,'Area');
%     area = cat(1,tmp.Area);
%     
%     for j=1:N
%         tmp = find(area==s(j));
%         clusters = length(tmp);
%         n(j,i) = clusters/num;
%     end
% end
% hold all
% legends = linspace(0,1,N);
% for i=1:N
%     plot(log(s),log(n(:,i)))
%     sprintf(tmp,'size = %d',s(i))
%     legend(tmp);
% end
%legend(legends)

L = 2.^(4:11);

P = 0.592;

n = zeros(N,length(L));
for i=1:length(L);
    L2 = L(i)*L(i);
    r = rand(L(i),L(i));
    z = r<P;
    [lw,num] = bwlabel(z,4);
    a = intersect(lw(1,:),lw(L(i),:));
    b = intersect(lw(:,1),lw(:,L(i)));
    u = union(a,b);
    tmp = regionprops(lw,'Area');
    area = cat(1,tmp.Area);
    for j=1:N
        tmp = find(area==s(j));
        clusters = length(tmp);
        n(j,i) = clusters/num;
    end
end
% plot(n)
% for i=1:N
%     plot(log(s),log(n(:,i)))
%     %sprintf(tmp,'size = %d',s(i))
%     legend(tmp);
% end