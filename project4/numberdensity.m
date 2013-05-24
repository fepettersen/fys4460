function[n,s] = numberdensity(p_in,L_in,N_in)

% Calculate the clusternumberdensity for a given 
% porosity, p, and system size, L. 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%-----------Cluster number density---------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


N = N_in;
% pc = 0.59275;
L = L_in;
r = rand(L,L);
p = p_in;
n = zeros(N,1);
% s = floor((1.8).^(0:N-1));
%innerend = length(s);


    z = r<p;
    [lw,num] = bwlabel(z,4);
    a = intersect(lw(1,:),lw(L,:));
    b = intersect(lw(:,1),lw(:,L));
    u = union(a,b);
    tmp = regionprops(lw,'Area');
    area = cat(1,tmp.Area);
    s = floor(exp(linspace(0,log(max(area)),N)));
    for j=1:N-1
        tmp = find(area==s(j));
        clusters = length(tmp);
        n(j,1) = clusters*s(j)/(L*L);
    end