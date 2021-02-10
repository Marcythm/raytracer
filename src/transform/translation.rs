use crate::utilities::prelude::*;
use crate::aabb::AABB;
use crate::transform::prelude::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct Translation {
    pub offset: Vec3,
}

impl Translation {
    pub fn new(offset: Vec3) -> Self {
        Self { offset }
    }

    pub fn set_offset(&mut self, offset: Vec3) {
        self.offset = offset;
    }
}

impl Transform for Translation {
    fn transform_point(&self, p: P3d) -> P3d {
        p + self.offset
    }

    fn inverse_transform_point(&self, p: P3d) -> P3d {
        p - self.offset
    }

    fn transform_vector(&self, v: Vec3) -> Vec3 {
        v
    }

    fn inverse_transform_vector(&self, v: Vec3) -> Vec3 {
        v
    }

    fn transform_box(&self, bounding_box: AABB) -> AABB {
        AABB::new(bounding_box.min + self.offset, bounding_box.max + self.offset)
    }

    fn inverse_transform_box(&self, bounding_box: AABB) -> AABB {
        AABB::new(bounding_box.min - self.offset, bounding_box.max - self.offset)
    }
}
