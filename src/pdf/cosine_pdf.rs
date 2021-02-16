use super::super::{
    utilities::prelude::*,
    pdf::prelude::*,
};

#[derive(Clone)]
pub struct CosinePDF {
    pub basis: ONB,
}

impl CosinePDF {
    pub fn new(normal: Vec3) -> Self {
        Self {
            basis: ONB::build_from(normal),
        }
    }
}

impl PDF for CosinePDF {
    fn value(&self, direction: Vec3) -> f64 {
        let cosine = direction.unit().dot(self.basis.w);
        if cosine <= 0.0 { 0.0 } else { cosine / PI }
    }

    fn generate(&self, rng: &mut SmallRng) -> Vec3 {
        self.basis.transform(Vec3::random_cosine_direction(rng))
    }
}
