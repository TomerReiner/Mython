package sample.types;

public abstract class Sequence extends Type {

    public Sequence() {
        this(false);
    }

    public Sequence(boolean isTemp) {
        super(isTemp);
    }

    @Override
    public abstract String getType();
}
