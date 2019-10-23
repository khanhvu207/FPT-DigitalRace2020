; Auto-generated. Do not edit!


(cl:in-package file_server-srv)


;//! \htmlinclude GetBinaryFile-request.msg.html

(cl:defclass <GetBinaryFile-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform ""))
)

(cl:defclass GetBinaryFile-request (<GetBinaryFile-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetBinaryFile-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetBinaryFile-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name file_server-srv:<GetBinaryFile-request> is deprecated: use file_server-srv:GetBinaryFile-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <GetBinaryFile-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader file_server-srv:name-val is deprecated.  Use file_server-srv:name instead.")
  (name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetBinaryFile-request>) ostream)
  "Serializes a message object of type '<GetBinaryFile-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetBinaryFile-request>) istream)
  "Deserializes a message object of type '<GetBinaryFile-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetBinaryFile-request>)))
  "Returns string type for a service object of type '<GetBinaryFile-request>"
  "file_server/GetBinaryFileRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetBinaryFile-request)))
  "Returns string type for a service object of type 'GetBinaryFile-request"
  "file_server/GetBinaryFileRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetBinaryFile-request>)))
  "Returns md5sum for a message object of type '<GetBinaryFile-request>"
  "e7a67f70bf777d8bfc72fa728a683c7d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetBinaryFile-request)))
  "Returns md5sum for a message object of type 'GetBinaryFile-request"
  "e7a67f70bf777d8bfc72fa728a683c7d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetBinaryFile-request>)))
  "Returns full string definition for message of type '<GetBinaryFile-request>"
  (cl:format cl:nil "string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetBinaryFile-request)))
  "Returns full string definition for message of type 'GetBinaryFile-request"
  (cl:format cl:nil "string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetBinaryFile-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetBinaryFile-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetBinaryFile-request
    (cl:cons ':name (name msg))
))
;//! \htmlinclude GetBinaryFile-response.msg.html

(cl:defclass <GetBinaryFile-response> (roslisp-msg-protocol:ros-message)
  ((value
    :reader value
    :initarg :value
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass GetBinaryFile-response (<GetBinaryFile-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetBinaryFile-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetBinaryFile-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name file_server-srv:<GetBinaryFile-response> is deprecated: use file_server-srv:GetBinaryFile-response instead.")))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <GetBinaryFile-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader file_server-srv:value-val is deprecated.  Use file_server-srv:value instead.")
  (value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetBinaryFile-response>) ostream)
  "Serializes a message object of type '<GetBinaryFile-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'value))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetBinaryFile-response>) istream)
  "Deserializes a message object of type '<GetBinaryFile-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'value) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'value)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetBinaryFile-response>)))
  "Returns string type for a service object of type '<GetBinaryFile-response>"
  "file_server/GetBinaryFileResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetBinaryFile-response)))
  "Returns string type for a service object of type 'GetBinaryFile-response"
  "file_server/GetBinaryFileResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetBinaryFile-response>)))
  "Returns md5sum for a message object of type '<GetBinaryFile-response>"
  "e7a67f70bf777d8bfc72fa728a683c7d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetBinaryFile-response)))
  "Returns md5sum for a message object of type 'GetBinaryFile-response"
  "e7a67f70bf777d8bfc72fa728a683c7d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetBinaryFile-response>)))
  "Returns full string definition for message of type '<GetBinaryFile-response>"
  (cl:format cl:nil "char[] value~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetBinaryFile-response)))
  "Returns full string definition for message of type 'GetBinaryFile-response"
  (cl:format cl:nil "char[] value~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetBinaryFile-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'value) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetBinaryFile-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetBinaryFile-response
    (cl:cons ':value (value msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetBinaryFile)))
  'GetBinaryFile-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetBinaryFile)))
  'GetBinaryFile-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetBinaryFile)))
  "Returns string type for a service object of type '<GetBinaryFile>"
  "file_server/GetBinaryFile")