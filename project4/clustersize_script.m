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