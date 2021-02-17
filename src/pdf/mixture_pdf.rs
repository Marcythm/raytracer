use super::super::{
    utilities::prelude::*,
    pdf::prelude::*,
};

#[derive(Clone)]
pub struct MixturePDF {
    pub pdf0: Rc<dyn PDF>,
    pub pdf1: Rc<dyn PDF>,
}

impl MixturePDF {
    pub fn new(pdf0: Rc<dyn PDF>, pdf1: Rc<dyn PDF>) -> Self {
        Self { pdf0, pdf1 }
    }
}

impl PDF for MixturePDF {
    fn value(&self, direction: Vec3) -> f64 {
        0.5 * (self.pdf0.value(direction) + self.pdf1.value(direction))
    }

    fn generate(&self, rng: &mut SmallRng) -> Vec3 {
        if rng.gen_range(0.0..1.0) < 0.5 {
            self.pdf0.generate(rng)
        } else {
            self.pdf1.generate(rng)
        }
    }
}
