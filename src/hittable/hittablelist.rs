use crate::ray::Ray;
use crate::hittable::*;

#[derive(Clone, Default)]
pub struct HittableList {
    objects: Vec<Rc<dyn Hittable>>,
}

impl HittableList {
    pub fn clear(&mut self) {
        self.objects.clear();
    }

    pub fn push<T: Hittable + 'static>(&mut self, object: T) {
        self.objects.push(Rc::new(object));
    }
    pub fn push_ptr<T: Hittable + 'static>(&mut self, ptr: Rc<T>) {
        self.objects.push(ptr);
    }
}

impl Hittable for HittableList {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let mut sol = None;
        let mut closest = t_max;

        for object in &self.objects {
            if let Some(subsol) = object.hit(&ray, t_min, closest) {
                closest = subsol.t;
                sol = Some(subsol);
            }
        }

        sol
    }
}
