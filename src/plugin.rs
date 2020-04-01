use log::error;
use qrcode_generator::{to_matrix, QrCodeEcc};
use samp::cell::string::{put_in_buffer, AmxString};
use samp::native;
use samp::prelude::*;
use samp::SampPlugin;

pub struct Plugin {}

impl SampPlugin for Plugin {}

impl Plugin {
    #[native(name = "QR_GetMatrix")]
    pub fn qr_get_matrix(
        &mut self,
        _: &Amx,
        input: AmxString,
        output: UnsizedBuffer,
        length: usize,
    ) -> AmxResult<i32> {
        match to_matrix(input.to_string(), QrCodeEcc::Low) {
            Ok(m) => {
                let mut dest = output.into_sized_buffer(length);
                let _ = put_in_buffer(
                    &mut dest,
                    m.into_iter()
                        .flatten()
                        .map(|b| if b { '1' } else { '0' })
                        .collect::<String>()
                        .as_ref(),
                );
                Ok(0)
            }
            Err(e) => {
                error!("{}", e);
                Ok(1)
            }
        }
    }
}
