close all
clear all

% lx = 256;
lx = 2.^(4:11);
ly = lx;
logbinsize = 2;
logbinmax = 11;

p = (0.2:0.05:0.6);
nx = size(p,2);

nsample = length(p);
Pi = zeros(nx,length(p));
P = zeros(nx,length(p));
l = {};
for i= 1:nx
    ll = lx(i)*ly(i);
    for isample = 1:nsample
        z = rand(lx(i),ly(i));
        zz = z<p(isample);
        [lw,num] = bwlabel(zz,4);
        perc_x = intersect(lw(:,1),lw(:,ly(i)));
        perc_y = intersect(lw(1,:),lw(lx(i),:));
        perc_xy = union(perc_x,perc_y);
        perc = find(perc_xy>0);
        s = regionprops(lw,'Area');
        clusterareas = cat(1,s.Area);
        
        if isempty(perc) ~= 1
            Pi(i,isample) = Pi(i,isample) +1;
            ar = sum(clusterareas(perc_xy(perc)));
            P(i,isample) = P(i,isample) + ar/ll;
        end
        
        ind = (1:num);
        indnoP = setxor(ind,perc_xy(perc));
        clusta = clusterareas(indnoP);
        [x,dx,n] = logbin(clusta,logbinsize,logbinmax);
        
        if (isample==1)
            nnsp = n/ll;
            nnsp = nnsp'./dx;
            nsp = nnsp;
        else
            nnsp = n/ll;
            nnsp = nnsp'./dx;
            nsp = nsp + nnsp
        end
    end
    P(i) = P(i)/nsample;
    Pi(i) = Pi(i)/nsample;
    nsp = nsp/nsample;
    ind2 = find(nsp>0);
    plot(log10(x(ind2)),log10(nsp(ind2)),'-o');
    hold all; 
%     drawnow;
    l{i} = [sprintf('p = %.4f',p(i))];
end
xlabel('clustersize')
ylabel('cluster numberdensity')
legend(l(:));
hold off;