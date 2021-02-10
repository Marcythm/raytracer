pub mod constant_medium;

pub mod prelude {
    pub use super::Medium;
}

use crate::hittable::prelude::*;

pub trait Medium: Hittable {

}
