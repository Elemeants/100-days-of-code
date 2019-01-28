// Testing new language 'RUST'

// Module 'Widget'
mod widget_module {
    // Structure 'Position' stores a (x, y) position
    #[derive(Copy,Clone)]
    pub struct Position {
        pub _x: u16,
        pub _y: u16
    }

    // Structure 'Widget' which store (id, position, width, height) data
    #[derive(Copy,Clone)]
    pub struct Widget {
        pub id: u8,
        pub position: Position,
        pub width: u16,
        pub height: u16
    }

    // Implementation to format how is Widget printed
    impl std::fmt::Display for Widget {
        fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
            write!(f, " Widget {} -> (x: {}, y: {}), (h: {}, w: {})", 
                self.id, 
                self.position._x, 
                self.position._y, 
                self.width, 
                self.height
            )
        }
    }

    // Module 'Widget_Factory' which transforms types into Widgets
    pub mod widget_factory {
        use super::Position;
        use super::Widget;
        pub fn new_widget(_id: u8, _position: Position, _width: u16, _height: u16) -> Widget {
            Widget{id: _id, position: _position, width: _width, height: _height}
        }

        pub fn gen_default_widget() -> Widget {
            Widget{id: 0, position: Position{_x: 1, _y: 1}, width: 2, height: 2}
        }
    }

    // Module 'Widget_Extensions' which implements extensions methods for Widgets
    pub mod widget_extensions {
        use super::Widget;
        pub trait Extensions {
            fn get_area(self) -> u16;
        }
        impl Extensions for Widget {
            fn get_area(self) -> u16 {
                self.width * self.height
            }
        }
    }
}

// Imports from module 'Widget'
use widget_module::Position;
use widget_module::Widget;
// use widget_module::widget_extensions::Extensions;
use widget_module::widget_factory;

// Main process
fn main() { 
    let widget = widget_factory::new_widget(1, Position{_x: 3, _y: 4}, 4, 5);
    let mut widgets: Vec<Widget> = Vec::new();
    widgets.push(widget);
    for _ in 0..5 {
        let w: Widget = widget_factory::gen_default_widget();
        widgets.push(w);
    }
    widgets.sort_by( |f1, f2| f1.width.cmp(&f2.width) );
    for widget in widgets.iter() {
        println!("{}", widget);
    }
}