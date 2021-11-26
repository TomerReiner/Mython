package sample.types;

public class Bool extends Type {

    private boolean value;

    public Bool(boolean value) {
        this.value = value;
    }

    public Bool(boolean isTemp, boolean value) {
        super(isTemp);
        this.value = value;
    }

    @Override
    public boolean isPrintable() {
        return true;
    }

    @Override
    public String toString() {
        return "" + (this.value ? "True" : "False");
    }

    @Override
    public String getType() {
        return "<type 'bool'>";
    }
}
