clear all;

pkg load signal
pkg load image
pkg load video
format compact  
% ustawienie formatu wyswietlania danych bez pustych linii
% the programm uses SSIM
% pomiar podobieñstwa strukturalnego

%S=SSIM("inCom1.avi","inCom1.avi")

S=SSIM("videoRO.avi","videoRO.avi")

S=SSIM("videoRO.avi","videoRE.avi")

S=SSIM("videoRO.avi","DeComH6r.avi")

S=SSIM("videoRO.avi","DeComH4r.avi")
