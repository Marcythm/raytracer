use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::aabb::AABB;
use crate::hittable::prelude::*;

#[derive(Clone)]
pub struct BVHNode { // Bounding Volume Hierarchy
    pub left         : Rc<dyn Hittable>,
    pub right        : Rc<dyn Hittable>,
    pub bounding_box : AABB,
}

impl BVHNode {
    pub fn new(hittables: HittableList, time0: f64, time1: f64, rng: &mut SmallRng) -> Self {
        Self::construct(hittables.hittables, time0, time1, rng)
    }

    pub fn construct(mut hittables: Vec<Rc<dyn Hittable>>, time0: f64, time1: f64, rng: &mut SmallRng) -> Self {
        if hittables.len() <= 0 {
            unreachable!("in BVHNode::construct(): length = 0");
        }
        if hittables.len() == 1 {
            Self {
                left         : hittables[0].clone(),
                right        : hittables[0].clone(),
                bounding_box : hittables.remove(0).bounding_box(time0, time1).unwrap(),
            }
        } else {
            let left;
            let right;
            let axis = rng.gen_range(0, 3);

            if hittables.len() == 2 {
                if hittables[0].bounding_box(time0, time1).unwrap().min[axis]
                 < hittables[1].bounding_box(time0, time1).unwrap().min[axis] {
                    left  = hittables[0].clone();
                    right = hittables[1].clone();
                } else {
                    left  = hittables[1].clone();
                    right = hittables[0].clone();
                }
            } else {
                hittables.sort_by(|lhs, rhs| {
                    lhs.bounding_box(time0, time1).unwrap().min[axis].partial_cmp(
                   &rhs.bounding_box(time0, time1).unwrap().min[axis]).unwrap()
                });

                let mut left_seq = hittables;
                let right_seq = left_seq.split_off(left_seq.len() / 2);

                left  = Rc::new(Self::construct(left_seq, time0, time1, rng));
                right = Rc::new(Self::construct(right_seq, time0, time1, rng));
            }

            Self {
                left         : left.clone(),
                right        : right.clone(),
                bounding_box : AABB::surrounding_box(
                    &left.bounding_box(time0, time1).unwrap(),
                    &right.bounding_box(time0, time1).unwrap()
                ),
            }
        }
    }
}

impl Hittable for BVHNode {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        if self.bounding_box.hit(ray, t_min, t_max) {
            if let Some(rec_l) = self.left.hit(ray, t_min, t_max) {
                if let Some(rec_r) = self.right.hit(ray, t_min, rec_l.t) {
                    Some(rec_r)
                } else {
                    Some(rec_l)
                }
            } else {
                if let Some(rec_r) = self.right.hit(ray, t_min, t_max) {
                    Some(rec_r)
                } else {
                    None
                }
            }
        } else {
            None
        }
    }

    fn bounding_box(&self, _: f64, _: f64) -> Option<AABB> {
        Some(self.bounding_box.clone())
    }
}
