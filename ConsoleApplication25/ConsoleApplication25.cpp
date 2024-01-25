#include <iostream>
#include <string>
#include <memory>

// Об'єкт знімку
class Memento {
public:
    Memento(const std::string& state) : state_(state) {}

    const std::string& getState() const {
        return state_;
    }

private:
    std::string state_;
};

// Об'єкт, стан якого можна зберігати та відновлювати
class Originator {
public:
    void setState(const std::string& state) {
        state_ = state;
        std::cout << "Originator: Setting state to " << state_ << "\n";
    }

    std::shared_ptr<Memento> createMemento() const {
        std::cout << "Originator: Creating Memento\n";
        return std::make_shared<Memento>(state_);
    }

    void restoreMemento(const std::shared_ptr<Memento>& memento) {
        state_ = memento->getState();
        std::cout << "Originator: Restoring state to " << state_ << "\n";
    }

private:
    std::string state_;
};

// Опікун, який відповідає за збереження та відновлення стану
class Caretaker {
public:
    void saveState(const std::shared_ptr<Memento>& memento) {
        memento_ = memento;
    }

    std::shared_ptr<Memento> getMemento() const {
        return memento_;
    }

private:
    std::shared_ptr<Memento> memento_;
};

int main() {
    // Використання паттерна "Знімок"
    Originator originator;
    Caretaker caretaker;

    // Встановлення стану та створення знімку
    originator.setState("State 1");
    caretaker.saveState(originator.createMemento());

    // Зміна стану та відновлення знімку
    originator.setState("State 2");
    originator.restoreMemento(caretaker.getMemento());

    return 0;
}
