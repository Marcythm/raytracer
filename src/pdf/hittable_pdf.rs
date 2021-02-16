use crate::utilities::prelude::*;
use crate::hittable::prelude::*;
use super::prelude::*;

#[derive(Clone)]
pub struct HittablePDF {
    pub hittable: Rc<dyn Hittable>,
    pub origin: P3d,
}

impl HittablePDF {
    pub fn new(hittable: Rc<dyn Hittable>, origin: P3d) -> Self {
        Self { hittable, origin }
    }
}

impl PDF for HittablePDF {
    fn value(&self, direction: Vec3) -> f64 {
        self.hittable.pdf_value(self.origin, direction)
    }

    fn generate(&self, rng: &mut SmallRng) -> Vec3 {
        self.hittable.random(self.origin, rng)
    }
}
