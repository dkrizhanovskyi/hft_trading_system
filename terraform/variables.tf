# terraform/variables.tf
variable "aws_region" {
  description = "Region where AWS resources will be created"
  default     = "us-west-2"
}