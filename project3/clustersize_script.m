
N = 200;
%n = zeros(N,N);
% nn = zeros(N,N);
%nnn = zeros(N,N);
pc = 0.59275;
p = linspace(0.45,0.6,11);
% p = [0.45,0.5,0.54,0.57,0.58];
s = zeros(length(p),N);
ss = zeros(length(p),N);
nn = zeros(length(p),N);
P = linspace(pc,0.9,N);
L = 2.^(4:11);
n = zeros(length(L),N);
nsamples = 1e4;
hold all

l = {};
for i=1:length(L)
    i
    for j=1:nsamples
        [ntmp,stmp] = numberdensity(pc,L(i),N);
        n(i,:) = n(i,:) + ntmp';
        s(i,:) = s(i,:) + stmp;
    %     [nn(i,:),s(i,:)] = numberdensity(p(i),2048,N);
    %     [nnn(i,:),ss(i,:)] = numberdensity(P(i),2048,N);
    end
    n(i,:) = n(i,:)./nsamples;
    s(i,:) = s(i,:)./nsamples;
%     plot(log10(s(i,:).*abs(p(i)-pc).^(1.0/0.4)),log10(nn(i,:).*s(i,:).^tau))
plot(log10(s(i,:)),log10(n(i,:)))
drawnow
l{i} = sprintf('L = %d',L(i));
end

legend(l)
xlabel('$$Clustersize; \log_{10}(s)$$','interpreter','latex')
ylabel('$$Cluster numberdensity; \log_{10}(n(s,p_c; L)$$','interpreter','latex')
% xlabel('$$\log_{10}(s\cdot abs(p-p_c)^{1/ \sigma})$$','interpreter','latex')
% ylabel('$$log_{10}(n(s,p)s^\tau)$$','interpreter','latex')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%----------------Mass scaling-----------------%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% nsamples = 15;
% l = {};
% M = zeros(length(L),1);
% % mass = zeros(length(L),1);
% hold all
% for j=1:length(L)
%     for i=1:nsamples;
%         L2 = L(j)*L(j);
%         r = rand(L(j),L(j));
%         z = r<pc;
%         [lw,num] = bwlabel(z,4);
%         a = intersect(lw(1,:),lw(L(j),:));
%         b = intersect(lw(:,1),lw(:,L(j)));
%         u = union(a,b);
%         tmp = regionprops(lw,'Area');
%         area = cat(1,tmp.Area);
%         if max(u)==0
%             M(j,1) = M(j,1) +1;
%         else
%             M(j,1) = M(j,1) + area(max(u));
%         end
%     end
%     M(j,1) = M(j,1)/nsamples;
% %     mass(j,1) = M(
% %     l{j} = sprintf('L = %d',L(j));
% %     loglog(L,M(j,:))
%     j
% end
% 
% plot(log10(L),log10(M(:,1)))
% % legend()
% xlabel('log(L)')
% ylabel('log(M)')