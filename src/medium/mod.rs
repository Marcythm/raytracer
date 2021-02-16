pub mod constant_medium;

pub mod prelude {
    pub use super::Medium;
}

use super::hittable::prelude::*;

pub trait Medium: Hittable {

}
