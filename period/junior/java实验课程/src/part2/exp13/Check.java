public class Check {
    public static void main(String... args) {
        Machine machine = new Machine();

        Goods[] goods = {
            new Goods("苹果", false), 
            new Goods("香蕉", false),
            new Goods("炸药", true),
            new Goods("胶卷", false)
        };
        for (Goods item : goods) {
            try {
                machine.checkBag(item);
                System.out.println(item.getName() + "检查通过。");
            } catch (DangerException e) {
                System.out.println(item.getName() + "是" + e.message + "被禁止。");
            }
        }
    }
}

class DangerException extends Exception {
    String message = "危险品！";
    
    public void toShow() {
        System.out.println(message);
    }
}

class Goods {
    String name;
    boolean isDangerous;

    Goods(String name, boolean isDangerous) {
        this.name = name;
        this.isDangerous = isDangerous;
    }

    String getName() {
        return name;
    }

    boolean isDangerous() {
        return isDangerous;
    }
}

class Machine {
    public void checkBag(Goods goods) throws DangerException {
        if (goods.isDangerous()) {
            throw new DangerException();
        }
    }
}
