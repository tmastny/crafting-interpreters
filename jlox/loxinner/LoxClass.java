package loxinner;

import java.util.List;
import java.util.Map;

class LoxClass implements LoxCallable {
  final String name;
  final LoxClass superclass;
  private final Map<String, LoxFunction> methods;

  LoxClass(String name, LoxClass superclass, Map<String, LoxFunction> methods) {
    this.superclass = superclass;
    this.name = name;
    this.methods = methods;
  }

  LoxFunction findMethod(String name) {
    // swapped version of usual.
    // first we try to find method on superclass. If it exists, we return that.
    LoxFunction fn = null;
    if (superclass != null) {
      fn = superclass.findMethod(name);
      if (fn != null) return fn;
    }

    if (methods.containsKey(name)) {
      return methods.get(name);
    }

    return null;
  }

  // doesn't quite work with chain of inheritances I think
  LoxFunction findSubMethod(String name) {
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
