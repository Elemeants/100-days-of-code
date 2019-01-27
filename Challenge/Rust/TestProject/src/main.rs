// Testing new language 'RUST'

mod widget_module {
    pub struct Position {
        pub _x: u16,
        pub _y: u16
    }

    pub struct Widget {
        pub id: u8,
        pub position: Position,
        pub width: u16,
        pub height: u16
    }

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

    pub mod widget_extensions {
        use super::Widget;
        pub fn sort(widgets: Vec<Widget>) {
            for widget in widgets.iter() {
                println!("{}", widget);
            }
        } 
    }
}

use widget_module::Position;
use widget_module::Widget;
// use widget_module::widget_extensions;
use widget_module::widget_factory;

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