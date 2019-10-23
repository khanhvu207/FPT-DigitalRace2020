;; Auto-generated. Do not edit!


(when (boundp 'file_server::GetBinaryFile)
  (if (not (find-package "FILE_SERVER"))
    (make-package "FILE_SERVER"))
  (shadow 'GetBinaryFile (find-package "FILE_SERVER")))
(unless (find-package "FILE_SERVER::GETBINARYFILE")
  (make-package "FILE_SERVER::GETBINARYFILE"))
(unless (find-package "FILE_SERVER::GETBINARYFILEREQUEST")
  (make-package "FILE_SERVER::GETBINARYFILEREQUEST"))
(unless (find-package "FILE_SERVER::GETBINARYFILERESPONSE")
  (make-package "FILE_SERVER::GETBINARYFILERESPONSE"))

(in-package "ROS")





(defclass file_server::GetBinaryFileRequest
  :super ros::object
  :slots (_name ))

(defmethod file_server::GetBinaryFileRequest
  (:init
   (&key
    ((:name __name) "")
    )
   (send-super :init)
   (setq _name (string __name))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass file_server::GetBinaryFileResponse
  :super ros::object
  :slots (_value ))

(defmethod file_server::GetBinaryFileResponse
  (:init
   (&key
    ((:value __value) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _value __value)
   self)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:serialization-length
   ()
   (+
    ;; char[] _value
    (* 1    (length _value)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; char[] _value
     (write-long (length _value) s)
     (dotimes (i (length _value))
       (write-byte (elt _value i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; char[] _value
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _value (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _value i) (sys::peek buf ptr- :char)) (incf ptr- 1)
     ))
   ;;
   self)
  )

(defclass file_server::GetBinaryFile
  :super ros::object
  :slots ())

(setf (get file_server::GetBinaryFile :md5sum-) "e7a67f70bf777d8bfc72fa728a683c7d")
(setf (get file_server::GetBinaryFile :datatype-) "file_server/GetBinaryFile")
(setf (get file_server::GetBinaryFile :request) file_server::GetBinaryFileRequest)
(setf (get file_server::GetBinaryFile :response) file_server::GetBinaryFileResponse)

(defmethod file_server::GetBinaryFileRequest
  (:response () (instance file_server::GetBinaryFileResponse :init)))

(setf (get file_server::GetBinaryFileRequest :md5sum-) "e7a67f70bf777d8bfc72fa728a683c7d")
(setf (get file_server::GetBinaryFileRequest :datatype-) "file_server/GetBinaryFileRequest")
(setf (get file_server::GetBinaryFileRequest :definition-)
      "string name
---
char[] value


")

(setf (get file_server::GetBinaryFileResponse :md5sum-) "e7a67f70bf777d8bfc72fa728a683c7d")
(setf (get file_server::GetBinaryFileResponse :datatype-) "file_server/GetBinaryFileResponse")
(setf (get file_server::GetBinaryFileResponse :definition-)
      "string name
---
char[] value


")



(provide :file_server/GetBinaryFile "e7a67f70bf777d8bfc72fa728a683c7d")


