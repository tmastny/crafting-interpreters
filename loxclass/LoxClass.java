package loxclass;

import java.util.List;
import java.util.Map;

interface LoxSuper {
  LoxFunction findMethod(String name);
  String name();
}

class LoxMetaClass implements LoxSuper {
  final LoxClass instance;
  private final Map<String, LoxFunction> methods;

  LoxMetaClass(String name, Map<String, LoxFunction> methods, Map<String, LoxFunction> statics) {
    this.instance = new LoxClass(name, methods, this);
    this.methods = statics;
  }

  public LoxFunction findMethod(String name) {
    if (methods.containsKey(name)) {
      return methods.get(name);
    }

    return null;
  }

  public String name() {
    return instance.name;
  }
}

class LoxClass extends LoxInstance implements LoxCallable, LoxSuper {
  private final Map<String, LoxFunction> methods;
  final String name;

  LoxClass(String name, Map<String, LoxFunction> methods, LoxSuper klass) {
    super(klass);
    this.name = name;
    this.methods = methods;
  }

  @Override
  public LoxFunction findMethod(String name) {
    if (methods.containsKey(name)) {
      return methods.get(name);
    }

    return null;
  }

  @Override
  public String toString() {
    return name;
  }

  @Override
  public String name() {
    return name;
  }

  @Override
  public Object call(Interpreter interpreter, List<Object> arguments) {
    LoxInstance instance = new LoxInstance(this);
    LoxFunction initializer = findMethod("init");
    if (initializer != null) {
      initializer.bind(instance).call(interpreter, arguments);
    }

    return instance;
  }

  @Override public int arity() {
    LoxFunction initializer = findMethod("init");
    if (initializer == null) return 0;
    return initializer.arity();
  }
}
