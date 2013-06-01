function[n,s] = numberdensity(p_in,L_in,N_in)

% Calculate the clusternumberdensity for a given 
% porosity, p, and system size, L. 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%-----------Cluster number density---------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


N = N_in;
% pc = 0.59275;
L = L_in;
%r = rand(L,L);
p = p_in;
n = zeros(N,1);
% s = floor((1.8).^(0:N-1));
%innerend = length(s);


    z = rand(L,L)<p;
    [lw,num] = bwlabel(z,4);
    a = intersect(lw(1,:),lw(L,:));
    b = intersect(lw(:,1),lw(:,L));
    %u = union(a,b);
    tmp = regionprops(lw,'Area');
    area = cat(1,tmp.Area);
    s = floor(exp(linspace(0,log(L*L),N)));
    for j=1:N-1
        ds = s(j+1) - s(j);
        tmp = find(area<=s(j+1) & area >=s(j));
        clusters = length(tmp)/ds;
%         n(j,1) = clusters*s(j)/(L*L);
        n(j,1) = clusters/(L*L);
    end

% hold all
% l = {};
% for i=1:length(p)
%     plot(log(n(:,i)))
%     l{i} = [sprintf('p = %g',p(i))];
% end
% legend(l(1:length(l)));

% L = 2.^(4:11);
% s = 2.^(0:N-1);
% s = fibonacci(200);
% P = pc;
% n = zeros(N,length(L));

% for i=1:length(L);
%     L2 = L(i)*L(i);
%     r = rand(L(i),L(i));
%     z = r<P;
%     [lw,num] = bwlabel(z,4);
%     a = intersect(lw(1,:),lw(L(i),:));
%     b = intersect(lw(:,1),lw(:,L(i)));
%     u = union(a,b);
%     tmp = regionprops(lw,'Area');
%     area = cat(1,tmp.Area);
%     for j=1:length(s)
%         tmp = find(area==s(j));
%         clusters = length(tmp);
%         n(j,i) = clusters/num;
%     end
% %     hold all;
% %     plot(log10(s),log10(n(:,i)))
% %     drawnow
% end
% 
% legend('L = 16','L = 32','L = 64','L = 128','L = 256','L = 512','L = 1024','L = 2048');
% hold off


