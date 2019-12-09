public class Cinema {
    public static void main(String... args) {
        new Cinema(20, 3);  // 创建一个20张票待售，3个窗口售票的Cinema。
    }

    Station[] stations;         // 售票窗口
    int totalTicketCount;       // 全部票的数量
    int soldTicketCount = 0;    // 已卖出票的数量

    Cinema(int ticketNumber, int stationNumber) {
        this.totalTicketCount = ticketNumber;
        prepareStations(stationNumber);  // 创建stationNumber个售票窗口。
        openStations();  // 各个售票窗口开始售票。
        waitUntilAllStationsAreClosed();  // 等待所有窗口结束售票。
        System.out.println("票卖完了！");
    }

    // 创建指定数量的售票窗口。
    private void prepareStations(int number) {
        stations = new Station[number];
        for (int i = 0; i < number; ++i) {
            stations[i] = new Station(this, "窗口" + (i+1));
        }
    }

    // 各个窗口开始售票。
    private void openStations() {
        for (Station station : stations) {
            station.start();
        }
    }

    // 阻塞直到所有的售票站关门。
    private void waitUntilAllStationsAreClosed() {
        for (Station station : stations) {
            try {
                station.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    // 返回未卖出的一张票的序号；若票已卖完则返回0。
    public synchronized int getTicket() {
        if (soldTicketCount < totalTicketCount) {
            ++soldTicketCount;
            return soldTicketCount;
        }
        return 0;
    }
}


class Station extends Thread {
    Cinema cinema;

    Station(Cinema cinema, String stationName) {
        super(stationName);
        this.cinema = cinema;
    }

    public void run() {
        while (true) {
            // 模拟等待顾客到来的时间。
            try {
                sleep((int)(Math.random() * 2000));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // 尝试向顾客售票。
            int ticket = cinema.getTicket();  // 从Cinema取票。
            if (ticket != 0) {  // 若成功取票，则卖出这张票。
                System.out.println(getName() + "卖出了第" + ticket + "张票。");
            }
            else {
                return; // 余票不足时关闭窗口。
            }
        }
    }
}
