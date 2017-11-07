fid = fopen('result', 'r');
tline = fgetl(fid);
data = [];
while ischar(tline)
    A = sscanf(tline, '%d %d %f');
    data = [data; A'];
    tline = fgetl(fid);
end
fclose(fid);


figure(1);
clf;

hold on;
for i=0:3
    subdata = data(data(:,2)==i,[1 3]);
    plot(subdata(:,1),subdata(:,2));
end
hold off;

set(gca,'XScale','log');
set(gca,'YScale','log');
axis([1 2e3 0 1]);
legend('binary heap','unsorted heap','fibonacci heap','cpp standard','Location','northwest');
set(gca,'Fontsize',20);
saveas(gcf,'fig1.png');

% figure(2);
% clf;
% 
% hold on;
% for i=0:3
%     subdata = data(data(:,2)==i,[1 3]);
%     plot(subdata(:,1),subdata(:,2));
% end
% hold off;
% 
% axis([10 400 0 2e-5]);
% set(gca,'XScale','log');
% legend('binary heap','unsorted heap','fibonacci heap','cpp standard','Location','northwest');
% set(gca,'Fontsize',20);
% saveas(gcf,'fig2.png');



